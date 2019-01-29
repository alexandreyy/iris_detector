#include "ift.h"
#include "weakclassifiers.c"
#include "features.c"


/* Train the ensemble of weak classifiers */

WeakClassifiers *TrainWeakClassifiers(iftMImage *mfeat, iftMImage *mlabel)
{
  int nclassifiers = mfeat->m/mlabel->m; /* number of features = number of classifiers */
  WeakClassifiers *wclass = CreateWeakClassifiers(nclassifiers); 
  int min_nerrors[nclassifiers];

  /* Set the initial minimum number of errors for each classifier */
  for (int c=0; c < nclassifiers; c++) {
    min_nerrors[c]   = IFT_INFINITY_INT;
  }

  /* Compute the threshold that produces the minimum number of errors
     for each classifier and set the weights of the classifiers to be
     inversely proportional to their minimum number of errors */
  
  for (int c=0; c < nclassifiers; c++) { /* for each classifier */
    for (int T=0; T < NormValue; T++) {  /* search for the optimum threshold by */
      int nerrors = 0;
      for (int j=0, f=c; j < mlabel->m; j++, f=f+nclassifiers) {  /* computing the total number of errors in all images */   
	for (int p=0; p < mfeat->n; p++) {
	  if ((mfeat->band[f].val[p]>=T)&&(mlabel->band[j].val[p]==0))
	    nerrors++; 
	  if ((mfeat->band[f].val[p]<T)&&(mlabel->band[j].val[p]!=0))
	    nerrors++; 
	}
      }
      if (nerrors < min_nerrors[c]){ /* and selecting the threshold with minimum number of errors. */
	min_nerrors[c]     = nerrors;
	wclass->thres[c]   = T;
      }
    }
  }

  /* Normalize in [0,1] the weights of the classifiers */
  
  float total_weight=0.0;
  for (int c=0; c < nclassifiers; c++) {
    wclass->weight[c] = ((float)mlabel->n*mlabel->m)/(min_nerrors[c]+0.00001);
    total_weight += wclass->weight[c];
  }

  for (int c=0; c < nclassifiers; c++) {
    wclass->weight[c] = wclass->weight[c]/total_weight;
  }
  
  return(wclass);
}


int main(int argc, char *argv[])
{
  
  if (argc != 3)
    iftError("Usage: iftTrainingForIrisDetection <path-to-training-images> <filename-to-save-the-weak-classifiers>","main");

  /* Load the complete path+filenames of the original and label images
     for training */
  
  iftFileSet *origSet  = iftLoadFileSetFromDirBySuffix(argv[1],"ppm");
  iftFileSet *labelSet = iftLoadFileSetFromDirBySuffix(argv[1],"pgm");

  if (origSet->n != labelSet->n)
    iftError("Number of original and label images are %d and %d, respectively. They must be equal","main",origSet->n,labelSet->n);

  /* Extract the features you have hand-crafted from each original
     image and create a single multiband image with the features from
     all images. Another option is to create an array of multiband
     images and store the features from each image in a different
     element of the array. */
  
  iftMImage  *mfeat=NULL;  /* multiband feature image */
  
  for (int i=0; i < origSet->n; i++) {
    printf("Processing file %s\n",origSet->files[i]->path);
    iftImage  *img     = iftReadImageByExt(origSet->files[i]->path);
    iftFImage *int_img = IntegralImage(img); /* compute the integral image */

    /* Extract each feature and append it as a new band */

    iftFImage *feat    = FeatureExtraction1(img); 
    AppendFeatures(&mfeat,feat);
    iftDestroyFImage(&feat);
    feat               = FeatureExtraction2(int_img); 
    AppendFeatures(&mfeat,feat);
    
    iftDestroyFImage(&feat);    
    iftDestroyFImage(&int_img);
    iftDestroyImage(&img);
  }
  
  /* Store the corresponding label images in a single multiband
     image. Another option is to create an array of label images. */
  
  iftMImage *mlabel = iftCreateMImage(mfeat->xsize,mfeat->ysize,mfeat->zsize,labelSet->n);
  
  for (int i=0; i < labelSet->n; i++) {
    printf("Loading label image %s\n",labelSet->files[i]->path);
    iftImage  *label  = iftReadImageByExt(labelSet->files[i]->path);
    for (int p=0; p < label->n; p++)
      mlabel->band[i].val[p]=label->val[p];
    iftDestroyImage(&label);
  }

  /* Create one weak classifier for each feature and train the
     ensemble of classifiers */

  printf("Training the weak classifiers by Adaboost\n");

  WeakClassifiers *wclass = TrainWeakClassifiers(mfeat, mlabel);

  printf("Writing the ensemble of weak classifiers\n");

  WriteWeakClassifiers(wclass,argv[2]);
    
  iftDestroyFileSet(&origSet);
  iftDestroyFileSet(&labelSet);
  iftDestroyMImage(&mfeat);
  iftDestroyMImage(&mlabel);
  DestroyWeakClassifiers(&wclass);
  
  return(0);
}




