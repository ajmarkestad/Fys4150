import numpy as np


def powerlaw(x,a,alpha,c):
    return a*np.power(x,alpha)+c

def findpowerlaw(x,y):
     from scipy.optimize import curve_fit
     import numpy as np

     top = int(np.argmax(y))
     end = np.nonzero(y)[0][-20]
     start = int(top+(end-top)*1./3.)
     xarray = np.array(x[start:end])
     yarray = np.array(y[start:end])
     guess = (100,-1,0)
     print(end)
     print(start)
     coeffs,pcov = curve_fit(powerlaw, xarray,yarray,  p0=guess)
     xvals = np.linspace(x[start],x[end],1000)
     yext = powerlaw(xvals,coeffs[0],coeffs[1],coeffs[2])
     #plt.plot(xarray,yarray,'ko')
     #plt.plot(xvals,yext)
     #plt.savefig('test1.png')
     #plt.close()
     perr = np.sqrt(np.diag(pcov))
     return coeffs, xvals, yext, perr