#Coding Rule

1. Follow Coding Standard   
[English](https://docs.google.com/document/d/1cT8EPgMXe0eopeHvwuFmbHG4TJr5kUmcovkr5irQZmo/edit)   
[Korean](https://docs.popekim.com/ko/coding-standards/cpp)   

2. Keep it simple.   
Don't put too many implementation in one class or one function.   

3. If possible, Use unique_ptr and shared_ptr.    
Why :   
For resource management, Never overrate yourself. You can make mistake.    
Smart pointer can have pointer of array also. So Use smart pointer.    
This let you free from making move, copy constructor.   

4. For performance, sacrifice memory.   
I don't release this game on mobile platform.  
So cache datas.    

5. If possible, Don't use static variable.   
You can't know in what order they are initialized, you can't constrol it.   
This can make bugs.   

6. Use Pointer instead of reference.     
I think this can be controversial.    
but For me, Pointer is better than reference.    
You can be in trouble if you usally use auto type.    
```c++
ClassA& GetClassAByReference()
{
	return classAInstance;
}

auto classA = GetClassAByReference();

```
What is the problem in this code??     
classA variable is copy-constructed with return value of GetClassAByReference.    
For me, sometimes I forgot putting & to auto specifier.    
And this was disaster.   

7. If possible, Implement RAII Style.    
This will prevent memory leak.     
