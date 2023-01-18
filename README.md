# bench_json4cpp
在确保有cmake和make工具的情况下，在项目根目录运行下列命令即可开始测试。
```shell
cmake -B build&&cd build&&make unittest&&cd bin&&./unittest
```
这是我本机的测试结果：
![benchmar](https://camo.githubusercontent.com/38b343adf6771eae2cd762b37ca0cf1346b188ff53e10381216fc32d093966e1/68747470733a2f2f696d672d626c6f672e6373646e696d672e636e2f64373965356138643933306134336666616335633261343435666233653837392e706e67)