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
xxx =  [x*0.1-5 for x in range(101)]
xx =  [x*0.1-4 for x in range(81)]
#print map(l20,xx)
plt.plot(xx,map(f,xx),'k',xx,map(l10,xx),'b',xx,map(l20,xx),'r')
plt.show()



