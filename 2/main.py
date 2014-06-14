from operator import mul
import matplotlib.pyplot as plt
def f(x):
    return 1.0/(1+16*x*x)
def gen_l(n):
    x = [x*10.0/n-5 for x in range(n+1)]
    return lambda xx: sum([f(x[k])*\
            reduce(mul,[xx-i for i in x if i!=x[k]])/reduce(mul,[x[k]-i for i in x if i!=x[k]])\
            for k in range(n+1)])
l10 = gen_l(10)
l20 = gen_l(20)
def f_range(s,d):
    return [x*d-s for x in range(int(1+2*s/d))]
xx =  f_range(4.0,0.01)
plt.plot(xx,map(f,xx),'k',xx,map(l10,xx),'b',xx,map(l20,xx),'r')
plt.show()
print l10(4.8),f(4.8),l10(4.8)-f(4.8)
print l20(4.8),f(4.8),l20(4.8)-f(4.8)


