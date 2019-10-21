此程序支持的功能如下：
所有功能支持命令行增加一个参数-v:支持动词形态的归一化
支持-n，-d，-s，-c，-f，-x，-p的位置互换，不过指令参数后面的文件或者数字要跟着指令互换位置，必须跟着对应的指令
所有文件名可以由含空格的文件名构成

功能0： 命令行参数-c:输出字母频率  
wf.exe -c ceshi6.txt 和 wf.exe -c ceshi6.txt -v dongci.txt 可以清楚的看出-v参数对结果的差别
wf.exe -c 1.I Have a Dream.txt

功能1： 命令行参数-f:输出文件中所有不重复的单词
wf.exe -f ceshi6.txt 和wf.exe -f ceshi6.txt -v dongci.txt 可以清楚的看出-v参数对结果的差别
wf.exe -f 1.I Have a Dream.txt

功能2： 命令行参数-d:对一个目录所有文件执行功能1 再加一个-s参数可以遍历目录下所有子目录
我的项目目录是C:\Users\Administrator\Desktop\Git\
wf.exe -d C:\Users\Administrator\Desktop\Git\Individual-Project\ConsoleApplication1\Debug\function2
wf.exe -d C:\Users\Administrator\Desktop\Git\Individual-Project\ConsoleApplication1\Debug\function2 -v dongci.txt 
wf.exe -d -s C:\Users\Administrator\Desktop\Git\Individual-Project\ConsoleApplication1\Debug\function2
wf.exe -d -s C:\Users\Administrator\Desktop\Git\Individual-Project\ConsoleApplication1\Debug\function2 -v dongci.txt 

功能3：支持-n参数，输出前number个数量最多的单词
wf.exe -d C:\Users\Administrator\Desktop\Git\Individual-Project\ConsoleApplication1\Debug\function2 -n 10
wf.exe -d C:\Users\Administrator\Desktop\Git\Individual-Project\ConsoleApplication1\Debug\function2 -v dongci.txt -n 10
wf.exe -d -s C:\Users\Administrator\Desktop\Git\Individual-Project\ConsoleApplication1\Debug\function2 -n 10
wf.exe -d -s C:\Users\Administrator\Desktop\Git\Individual-Project\ConsoleApplication1\Debug\function2 -v dongci.txt -n 10

功能4：命令行参数-x 功能1扩展 支持停词表
wf.exe -x stopwords.txt  -f 1.I Have a Dream.txt
wf.exe -x stopwords.txt  -f 1.I Have a Dream.txt -v dongci.txt

功能5：命令行参数-p（ wf.exe -p <number>  <file> ） 输出number个词的短语
wf.exe -p 5 1.I Have a Dream.txt
wf.exe -p 5 1.I Have a Dream.txt -v dongci.txt




