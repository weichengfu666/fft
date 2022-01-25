# 使用说明

> 本测试用例用于测试傅里叶级数

## 编译 & 运行

- 拷贝至  `cinos/service/test/FFT`
- 上层 `Kbuild` 文件 加入 `obj-y += FFT/`
- 同操作系统编译一样

    ```sh
    make distclean
    configure.sh sun8iw11p
    make
    ```

- 编译完成后会在微内核源码根目录生成`kernel.bin`
- 将其拷贝到SD卡根目录
- 叉卡上电运行
- 执行以下命令运行
    `c_exec fft_test num1 num2 num3 num4`
  - `c_exec` 微内核指令固定
  - `fft_test` 程序名称
  - `num1` 输入数据包含的波形数
  - `num2` 输入数据采样数必须为2的N次方
  - `num3` 重复计算次数 ( 便于计时 )
  - `num4` 可选(缺省值为0) - 快速傅里叶变换换标志
    - "-i" : inverse FFT (反变换)
    - 其他 : forward FFT (正变换)
- 如:
`c_exec fft_test 4 1024 10`
---

**备注:**

- fft运算任务结束后会打印出耗时信息
- 由于微内核时间片为20ms, 运算时间较短时参考意义不大, 可以通过重复运算多次 ( 对应参数num3 ) 的方式实现
- 测试结果信息保存在SD卡根目录 `fourier_out.txt` 中, 以备参考
