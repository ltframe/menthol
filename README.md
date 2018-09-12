<div align=center><img src="http://www.ltplayer.com/static/images/gitlogo.png"/></div>


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
null import _mmain def var in
```

###### 操作符
```html
- * / () ; , | &  ? [] ! % ^ : :: .. = < > != <> || &&  >= <= == += -= /= *= %= &= |= ^= << >> **
```



###### 基本操作
所有的menthol都由系统自动执行_mmain开始,声明变量使用关键字var,全部变量要在变量名前加@,局部变量要在变量名前加$
```html
var @global;// 全局变量
_mmain:$a,$c
{    
	var $v = 0; //局部变量
}
```
###### 错误处理

```html
def test:
{
    
    throw "msg1","msg2";
}

_mmain:$a,$c
{    
	try{
		test();
	}
	except:$a,$b
	{
		MIo.Out($a);
		MIo.Out($b);
	}
}

```
###### 与外部扩展的交互
* C/C++ 调用Menthol
* Menthol调用c/c++

```html
import "example1";

def test:$i
{    
	MIo.Out($i[0]);
}
_mmain:$a,$c
{    
	example1.test();
    example1.CallBack(test);
}

```

###### 数组

```html
_mmain:$a,$c
{    
	var $arr = {1,2,3,4,5,6};
	MIo.Out($arr[1]);
	MIo.Out($arr[1..][1]);
	MIo.Out($arr[..3][1]);
	MIo.Out($arr[2..5][1]);
	$arr = "abcdefghi";
	MIo.Out($arr[1]);
}


```




###### 字典

```html

import "MDict";
_mmain:$a,$c
{    
    var $arr = {1,2,3,4,6,7};
	for(var $i in $arr)
	{
		MIo.Out($i);
	}
	$arr ="abcdefghi";
	for(var $i in $arr)
	{
		MIo.Out($i);
	}
	$arr =(key1::"key1",key2::"key2");
	for(var $i in $arr)
	{
		MIo.Out(MDict.GetKey($arr,$i));
		MIo.Out(MDict.GetValue($arr,$i));
	}
}

```


###### 自定义包
packagetest.mep


```html


import "MIo";
var @g;

def func:
{    
	MIo.Out("package function called");
}

def func1:$i
{
	func();
	MIo.Out($i)
}

def callback:$func
{
	MIo.Out(@g);
	func();
	$func()
}

```

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

MentholPackMethod void example1_Init()
{
    RegisterPackAgeFunciton("test",test,0);	

}

```


