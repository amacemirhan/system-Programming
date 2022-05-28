n=1500
top=0.0
sign=True
for i in range(1,n):
    if (i%2==1):
    	print(i , "  " , 1.0/i)
        if sign==True:
            top+=1.0/i
            sign=False
        else:
            top-=1.0/i
            sign=True
pi=top*4
print(top)
print(pi)
