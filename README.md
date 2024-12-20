



# Menthol
Menthol是一个简单、易用、易学的脚本语言,语法简单,开发简便,使用C/C++可以快速为它开发扩展.关于更多信息请访问官方网站:[www.ltplayer.com][11]

## 特性
* 无类型
* 自动内存管理
* 面向函数编程
* 方便的函数封装
* 简便的方法扩展


## 教程说明

###### 关键字
```html
if else for break true false const
try except throw continue return while
null import _mmain def var in typeof module use mmrt
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
所有的menthol都由系统自动执行_mmain开始,声明变量使用关键字var,全部变量要在变量名前加@,局部变量要在变量名前加$,不可以修改的变量前面要用const修饰
```html
module test
{
	var @global;// 全局变量
	var const @global2;// const 全局变量
}
_mmain:$a,$c
{    
	var $v = 0; //局部变量
	var cosnt $v2 = 0; //const 局部变量
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
	var $m = mmrt(Console);
	try{
		mmrt(test).test();
	}
	except:$a,$b
	{
		$m.Out($a);
		$m.Out($b);
	}
}

```

###### 数组

```html
Import console;
use Console;
_mmain:$a,$c
{    
	var $m = mmrt(Console);
	var $arr = [1,2,3,4,5,6];
	$m.Out($arr[1]);
	$m.Out($arr[1..][3]);
	$m.Out($arr[..3][4]);
	$m.Out($arr[2..5][5]);
	$arr = "abcdefghi";
	$m.Out($arr[1]);
}


```




###### 字典

```html
Import console;
use Console;
_mmain:$a,$c
{    
	var $m = mmrt(Console);
    var $arr = [1,2,3,4,6,7];
	for(var $i in $arr)
	{
		$m.Out($i);
	}
	$arr ="abcdefghi";
	
	for(var $i in $arr)
	{
		$m.Out($i);
	}
	$arr =(key1::"value1",key2::"value2");
	for(var $key,$value in $arr)
	{
		$m.Out($key+":"+$value);
	}
}

```


###### 函数

```html
Import console;
use Console;
module test
{
	var @m = mmrt(Console);
	def func:$i1,$i2=333
	{	
		@m.Out($i1);
		@m.Out($i2);
	}
}
_mmain:$a,$c
{	
	var $t = mmrt(test);
	$t.func(222,1000,333);
	$t.func(555);
}


```


###### 多线程

```html
import console;
import Thread;
use Console,Thread;

module test
{
	var @m = mmrt(Console);
	def thread2:
	{
		while(true){
			@m.Out("thread2");
		}
	}

	def thread1:
	{
		while(true){
			@m.Out("thread1");
		}
	}
}
_mmain:$a,$c
{	
	var $t = mmrt(Thread),$e = mmrt(test);
	var $k1 = $t.NewThread($e.thread1);
	$t.Join($k1);
	var $k2 = $t.NewThread($e.thread2);	
	$t.Join($k2);
}

```
<div align=left>
<img src="http://www.ltplayer.com/doc/menthol14/images/thread.png"/></div>


###### 开发外部扩展库(c/c++)
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
关于更多的menthol的相关文档，请浏览[menthol文档][10]


  [2]: https://github.com/ltframe/menthol
  [3]: http://www.ltplayer.com/doc/menthol14/index.html
  [4]: http://www.ltplayer.com/doc/menthol14/index.html
  [5]: http://www.ltplayer.com/doc/menthol14/index.html
  [6]: http://www.ltplayer.com/doc/menthol14/index.html
  [7]: http://www.ltplayer.com/doc/menthol14/index.html
  [8]: http://www.ltplayer.com/doc/menthol14/index.html
  [9]: http://www.ltplayer.com/doc/menthol14/index.html
  [10]: http://www.ltplayer.com/doc/menthol14/index.html
  [11]: http://www.ltplayer.com/