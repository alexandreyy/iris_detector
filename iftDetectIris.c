#include "ift.h"
#include "weakclassifiers.c"
#include "features.c"

iftMImage *WeakClassifyImages(iftMImage *mfeat, WeakClassifiers *wclass)
{
  iftMImage *mlabel = iftCreateMImage(mfeat->xsize,mfeat->ysize,mfeat->zsize,mfeat->m/wclass->nclassifiers);
  
  for (int j=0, b=0; j < mlabel->m; j++, b=b+wclass->nclassifiers) {    
    for (int p=0; p < mlabel->n; p++) {
      for (int f=0; f < wclass->nclassifiers; f++) {
	if (mfeat->band[b+f].val[p]>=wclass->thres[f])
	  mlabel->band[j].val[p] += 255*wclass->weight[f];
      }
    }
  }
  
  return(mlabel);
}

iftVoxel ObjectCentroid(iftImage *mask)
{
  iftVoxel c;
  float x=0,y=0,n=0;

  for (int p=0; p < mask->n; p++){
    if (mask->val[p]!=0){
      n++; x+=iftGetXCoord(mask,p); y+=iftGetYCoord(mask,p);
    }
  }
  if (n > 0){
    x /= n; y /= n;
  }
  c.x = iftRound(x);
  c.y = iftRound(y);
  c.z = 0;
  return(c);
}

iftMImage *ExtractRegionOfInterest(iftMImage *morig, iftMImage *mlabel, float radius)
{
  iftMImage *mroi = iftCreateMImage(2*radius+1,2*radius+1,1,morig->m);
  iftAdjRel *A=iftCircular(sqrtf(2.0)); /* 8-neighbors */

  for (int b=0; b < mlabel->m; b++) {
    iftImage *label  =  iftMImageToImage(mlabel, NormValue, b); /* get label image b */
    int       maxval =  iftMaximumValue(label); /* select is brightest objects */
    for (int p=0; p < label->n; p++){
      if (label->val[p]!=maxval)
	label->val[p]=0;
    }
    iftImage *mask   = iftSelectLargestComp(label,A); /* select the
							 largest
							 object among
							 the brightest
							 ones */
    /* iftCloseBasins ou iftClose estão no iftMathMorph.h em include */
    
    iftVoxel c = ObjectCentroid(mask); /* find its centroid */
    
    iftDestroyImage(&label);
    iftDestroyImage(&mask);

    /* copy the region of interest from the original images */
    iftVoxel u; u.z = 0;
    int q = 0;
    for (u.y=c.y-radius; u.y <= c.y+radius; u.y++) {
      for (u.x=c.x-radius; u.x <= c.x+radius; u.x++){ 	
	if (iftMValidVoxel(morig,u)){
	  float dist = sqrtf((u.y-c.y)*(u.y-c.y)+(u.x-c.x)*(u.x-c.x));
	  if (dist <= radius){
	    int p = iftMGetVoxelIndex(morig,u);
	    mroi->band[b].val[q] = morig->band[b].val[p];
	  }else
	    mroi->band[b].val[q] = 0;
	  q++;
	}
      }
    }
  }

  iftDestroyAdjRel(&A);
  
  return(mroi);
}

int main(int argc, char *argv[])
{

  if (argc != 3)
    iftError("Usage: iftDetectIris <path-to-test-images> <filename-to-load-the-weak-classifiers>","main");

  /* Load the complete path+filenames of the original images for
     testing and load the ensemble of weak classifiers */
  
  iftFileSet      *origSet  = iftLoadFileSetFromDirBySuffix(argv[1],"ppm");
  WeakClassifiers *wclass   = ReadWeakClassifiers(argv[2]);

  /* Load the original images in a single multiband image, extract the
     features you have hand-crafted from them, and create another
     single multiband feature image with the features from all
     images. */
  
  iftMImage  *mfeat = NULL;  /* multiband feature image */
  iftImage   *img   = iftReadImageByExt(origSet->files[0]->path);
  iftMImage  *morig = iftCreateMImage(img->xsize,img->ysize,img->zsize,origSet->n);
  iftDestroyImage(&img);
  
  for (int i=0; i < origSet->n; i++) {
    printf("Processing file %s\n",origSet->files[i]->path);
    img                = iftReadImageByExt(origSet->files[i]->path);
    for(int p=0; p < morig->n; p++) /* copy image to a corresponding band */
      morig->band[i].val[p] = img->val[p];
    
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


  /* Classify images */
  
  iftMImage *mlabel = WeakClassifyImages(mfeat,wclass);
  iftDestroyMImage(&mfeat);
  DestroyWeakClassifiers(&wclass);

  if (!iftDirExists("./tmp"))
    iftMakeDir("./tmp");

  for (int b=0; b < mlabel->m; b++) {    
    iftImage *img  = iftMImageToImage(mlabel,NormValue,b);
    char *filename = iftFilename(origSet->files[b]->path,"/");
    char *basename = iftBasename(filename);
    char *basename_withpath = iftJoinPathnames("./tmp", basename);
    char  pathname[200];
    sprintf(pathname,"%s.pgm",basename_withpath);

    printf("Writing %s\n",pathname);
    iftWriteImageByExt(img,pathname);
    iftDestroyImage(&img);
    iftFree(basename);
    iftFree(basename_withpath);
    iftFree(filename);
  }


  
  /* Extract region of interest from all images */
  
  iftMImage *mroi = ExtractRegionOfInterest(morig, mlabel, 150.0);
  iftDestroyMImage(&morig);
  iftDestroyMImage(&mlabel);

  /* Write cropped images in ./tmp */
  
  if (!iftDirExists("./tmp"))
    iftMakeDir("./tmp");

  for (int b=0; b < mroi->m; b++) {    
    iftImage *img  = iftMImageToImage(mroi,NormValue,b);
    char *filename = iftFilename(origSet->files[b]->path,"/");
    char *basename = iftBasename(filename);
    char *basename_withpath = iftJoinPathnames("./tmp", basename);
    char  pathname[200];
    sprintf(pathname,"%s.png",basename_withpath);

    printf("Writing %s\n",pathname);
    iftWriteImageByExt(img,pathname);
    iftDestroyImage(&img);
    iftFree(basename);
    iftFree(basename_withpath);
    iftFree(filename);
  }

  iftDestroyFileSet(&origSet);
  iftDestroyMImage(&mroi);
  
  return(0);
}
