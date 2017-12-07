import numpy as np

def rSquare(estimations, measureds):
    """ Compute the coefficient of determination of random data. 
    This metric gives the level of confidence about the model used to model data"""
    SEE =  (( np.array(measureds) - np.array(estimations) )**2 ).sum()
    mMean = (np.array(measureds)).sum() / float(len(measureds))
    dErr = ((mMean - measureds)).sum()
    
    return 1 - (SEE / dErr)