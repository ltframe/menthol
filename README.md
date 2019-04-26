<div align=center>
	<img src="http://www.ltplayer.com/images/gitlogo.png"/></div>


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
All menthol programs start with the system automatically executing _mmain, using the keyword var to declare variables, all global variables must start with @, and there should be a $ in front of the local variable.
```html
module test
{
	var @global;// global variable
}
_mmain:$a,$c
{    
	var $v = 0; //local variable
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
	Console.Out($arr[1..][1]);
	Console.Out($arr[..3][2]);
	Console.Out($arr[2..5][3]);
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
StackState test()
{
    StackState value =GetParam(1);
	StackState st;
	st.v = M_STRING;
	st = String_CreateString("this is a test string");
	return st;
}

UserFunctionAtter example1list[] = {
	{ "test", test, 0 },
	{NULL,NULL,0}
};

MentholPackMethod void example1_Init()
{
    RunTimeState* prt = CreateModuleRunTime("example1");
	RegisterModuleFunciton(prt, example1list);
}

```
For more information on menthol, please visit [menthol document][4]

----------


# Menthol
Menthol是一个简单、易用、易学的脚本语言,语法简单,开发简便,使用C/C++可以快速为它开发扩展

## 特性
* 无类型
* 自动内存管理
* 面向函数编程
* 方便的函数封装
* 简便的方法扩展


## 教程说明

###### 关键字
```html
if else for break true false
try except throw continue return while
null import _mmain def var in typeof module use
```

###### 操作符
```html
- * / () ; , | &  ? [] ! % ^ : :: .. = < > != <> || &&  >= <= == += -= /= *= %= &= |= ^= << >> **
```
###### 基本概念
menthol是一个函数式语言，但它是基于模块操作的语言，在menthol,除了启动函数_mmain，其他用户定义的全局变量、函数都必须基于模块而定义.

###### 导入包
包就是一个用menthol语言或者C/C++写成的模块集合，扩展名为.med,如果要使用包中的模块，需要用import关键字导入

    Import console;

console是系统自带的输入输出包，里面包含了控制输入输出的模块，导入时不需要区分文件大小写.

###### 使用模块
导入包以后，就可以使用包内的模块了，使用前需要用use关键字来使用，注意，模块名是去区分大小写的,在一个use后面可以引入多个模块名，用逗号隔开

    Import console;
    use Console;

如果要导入文件夹中的包，可以用'.'来代替文件路径中的'/',如要导入iup的IupControlsStandard,使用button,可以使用

	Import iup.controlsstandard;
	use IupControlsStandard;

如果使用的模块在同一包内，并且在使用前已经定义，则不要用use在引入

###### 基本操作
所有的menthol都由系统自动执行_mmain开始,声明变量使用关键字var,全部变量要在变量名前加@,局部变量要在变量名前加$
```html
module test
{
	var @global;// 全局变量
}
_mmain:$a,$c
{    
	var $v = 0; //局部变量
}
```
###### 错误处理

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

###### 数组

```html
Import console;
use Console;
_mmain:$a,$c
{    
	var $arr = [1,2,3,4,5,6];
	Console.Out($arr[1]);
	Console.Out($arr[1..][5]);
	Console.Out($arr[..3][6]);
	Console.Out($arr[2..5][7]);
	$arr = "abcdefghi";
	Console.Out($arr[1]);
}


```




###### 字典

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


###### 函数

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


###### 多线程

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
Menthol使用iup作为实现界面的类库

<div align=left>
<img src="http://www.ltplayer.com/images/mentholhtmlimg/iup2.png"/></div>


###### 开发外部扩展库(c/c++)
example1.dll

```cpp
#include "Menthol.h"
StackState test()
{
    StackState value =GetParam(1);
	StackState st;
	st.v = M_STRING;
	st = String_CreateString("this is a test string");
	return st;
}

UserFunctionAtter example1list[] = {
	{ "test", test, 0 },
	{NULL,NULL,0}
};

MentholPackMethod void example1_Init()
{
    RunTimeState* prt = CreateModuleRunTime("example1");
	RegisterModuleFunciton(prt, example1list);
}

```
关于更多的menthol的相关文档，请浏览[menthol文档][8]


  [1]: http://www.ltplayer.com/doc/menthol/index.html
  [2]: http://www.ltplayer.com/doc/menthol/index.html
  [3]: http://www.ltplayer.com/doc/menthol/index.html
  [4]: http://www.ltplayer.com/doc/menthol/index.html
  [5]: http://www.ltplayer.com/doc/menthol/index.html
  [6]: http://www.ltplayer.com/doc/menthol/index.html
  [7]: http://www.ltplayer.com/doc/menthol/index.html
  [8]: http://www.ltplayer.com/doc/menthol/index.html