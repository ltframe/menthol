# Menthol
Menthol是一个简单、易用、易学的脚本语言,语法简单,开发简便,使用C/C++可以快速为它开发扩展

## 特性
* 无类型
* 自动内存管理
* 面向函数编程
* 方便的函数封装
* 简便的方法扩展


## 代码示例


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