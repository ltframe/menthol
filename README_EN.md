<div align=center>
	<img src="http://www.ltplayer.com/images/gitlogo.png"/></div>


[Englist][1] | [简体中文][2]

# Menthol
Menthol is an easy-to-use, easy-to-learn scripting language with a simple syntax and easy development. With C / C++, you can quickly develop extension methods.


## Teatures
* No type
* Automatic memory management
* Functional programming
* Convenient feature pack
* Simple feature extension development


## Tutorial

###### Keywords
```html
if else for break true false
try except throw continue return while
null import _mmain def var in typeof module use
```

###### Operators
```html
- * / () ; , | &  ? [] ! % ^ : :: .. = < > != <> || &&  >= <= == += -= /= *= %= &= |= ^= << >> **
```
###### Basic concepts
Menthol is a functional language, but it is a module-based language. In menthol, in addition to the startup function _mmain, other user-defined functions, such as global variables and functions, must be defined based on the module.

###### Use package
A package is a collection of modules written in Mint or C/C++ with a .med extension. If you want to use a module in a package, you need to import it using the import keyword.

    Import console;

The console is the system's own input and output package, which contains modules that control the inputs and outputs. There is no need to distinguish between file cases when importing.


###### use module
After importing the package, you can use the modules inside the package. You need to use the use keyword before using it. Note that the module name is case sensitive. You can introduce multiple module names after use, separated by commas.

    Import console;
    Use the Console;


If you want to import the package in the folder, you can use '.' instead of the '/' in the file path. To import the Iup's IupControlsStandard, use the button to use

	Import iup.controlsstandard;
	use IupControlsStandard;


If you are using modules that are in the same package and defined before use, you do not need to reintroduce them using the use keyword.



###### Variable concept
All menthol programs start with the system automatically executing _mmain, using the keyword var to declare variables, all global variables must start with @, and there should be a $ in front of the local variable.Variables that cannot be modified are preceded by const
```html
module test
{
	var @global;// global variable
	var const @global;// const global variable
}
_mmain:$a,$c
{    
	var $v = 0; //local variable
	var const $v2 = 0; //const local variable
}
```
###### Error handling

```html
Import console;
use Console;
module test
{
	def test:
	{	    
	    throw "msg1","msg2";
	}
}

_mmain:$a,$c
{    
	try{
		test.test();
	}
	except:$a,$b
	{
		Console.Out($a);
		Console.Out($b);
	}
}

```

###### Array

```html
Import console;
use Console;
_mmain:$a,$c
{    
	var $arr = [1,2,3,4,5,6];
	Console.Out($arr[1]);
	Console.Out($arr[1..][3]);
	Console.Out($arr[..3][4]);
	Console.Out($arr[2..5][5]);
	$arr = "abcdefghi";
	Console.Out($arr[1]);
}


```




###### Dictionary

```html
Import console;
use Console;
_mmain:$a,$c
{    
    var $arr = [1,2,3,4,6,7];
	for(var $i in $arr)
	{
		Console.Out($i);
	}
	$arr ="abcdefghi";
	for(var $i in $arr)
	{
		Console.Out($i);
	}
	$arr =(key1::"value1",key2::"value2");
	for(var $key,$value in $arr)
	{
		Console.Out($key+":"+$value);
	}
}

```


###### Funciton

```html
Import console;
use Console;
module test
{
	def func:$i1,$i2=333
	{	
		Console.Out($i1);
		Console.Out($i2);
	}
}
_mmain:$a,$c
{	
	test.func(222,1000,333);
	test.func(555);
}

```

###### threading

```html
import console;
import Thread;
use Console,Thread;

module test
{
	def thread2:
	{
		while(true){
			Console.Out("thread2");
		}
	}

	def thread1:
	{
		while(true){
			Console.Out("thread1");
		}
	}
}
_mmain:$a,$c
{	
	var $k1 = Thread.NewThread(test.thread1);
	Thread.Join($k1);
	var $k2 = Thread.NewThread(test.thread2);	
	Thread.Join($k2);
}

```
<div align=left>
<img src="http://www.ltplayer.com/images/mentholhtmlimg/thread.png"/></div>



###### Gui
Menthol uses iup as a class library for implementing interfaces

<div align=left>
<img src="http://www.ltplayer.com/images/mentholhtmlimg/iup2.png"/></div>



###### Develop an external extension library (c / c ++)
example1.dll

```cpp
#include "Menthol.h"
StackState test(VmState* vmstate)
{
    StackState value =GetParam(1,vmstate);
	StackState st;
	st.v = M_STRING;
	st = String_CreateString("this is a test string",vmstate);
	return st;
}

UserFunctionAtter example1list[] = {
	{ "test", test, 0 },
	{NULL,NULL,0}
};

MentholPackMethod void example1_Init(VmState* vmstate)
{
    RunTimeState* prt = CreateModuleRunTime("example1",vmstate);
	RegisterModuleFunciton(prt, example1list);
}

```
For more information on menthol, please visit [menthol document][6]


  [1]: https://github.com/ltframe/menthol/blob/master/README.md
  [2]: https://github.com/ltframe/menthol/blob/master/README_CN.md
  [3]: http://www.ltplayer.com/doc/menthol/index.html
  [4]: http://www.ltplayer.com/doc/menthol/index.html
  [5]: http://www.ltplayer.com/doc/menthol/index.html
  [6]: http://www.ltplayer.com/doc/menthol/index.html