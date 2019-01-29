#define NormValue 255.0 /* maximum feature value and maximum
			   prediction value for the purpose of feature
			   normalization and prediction visualization. */

/* Ensemble of weak classifiers */

typedef struct _weak_classifiers {
  float *thres, *weight; /* threshod and weight of each classifier */
  int    nclassifiers;   /* number of classifiers */
} WeakClassifiers;

WeakClassifiers *CreateWeakClassifiers(int nclassifiers);
void             DestroyWeakClassifiers(WeakClassifiers **wclass);
WeakClassifiers *ReadWeakClassifiers(char *filename);
void             WriteWeakClassifiers(WeakClassifiers *wclass, char *filename);

/* Create an ensemble of weak classifiers and initialize the weight of
   each classifier */

WeakClassifiers *CreateWeakClassifiers(int nclassifiers)
{
  WeakClassifiers *wclass = (WeakClassifiers *)calloc(1,sizeof(WeakClassifiers));

  wclass->thres  = iftAllocFloatArray(nclassifiers);
  wclass->weight = iftAllocFloatArray(nclassifiers);
  wclass->nclassifiers = nclassifiers;

  for (int i=0; i < nclassifiers; i++){
    wclass->weight[i]=1.0;
  }

  return(wclass);
}

/* Destroy the classifiers from memory */

void DestroyWeakClassifiers(WeakClassifiers **wclass)
{
  if (*wclass != NULL){
    iftFree((*wclass)->thres);
    iftFree((*wclass)->weight);
    iftFree(*wclass);
    *wclass = NULL;
  }
}

/* Write weak classifiers to disk */

void WriteWeakClassifiers(WeakClassifiers *wclass, char *filename)
{
  FILE *fp = fopen(filename,"w");

  fprintf(fp,"%d\n",wclass->nclassifiers);
  for (int c=0; c < wclass->nclassifiers; c++)
    fprintf(fp,"%f %f\n",wclass->thres[c],wclass->weight[c]);

  fclose(fp);  
}

/* Read weak classifiers from disk */

WeakClassifiers *ReadWeakClassifiers(char *filename)
{
  WeakClassifiers *wclass;
  int nclassifiers;
  
  FILE *fp = fopen(filename,"r");

  fscanf(fp,"%d",&nclassifiers);
  wclass = CreateWeakClassifiers(nclassifiers);
  
  for (int c=0; c < wclass->nclassifiers; c++)
    fscanf(fp,"%f %f",&wclass->thres[c],&wclass->weight[c]);

  fclose(fp);

  return(wclass);
}

