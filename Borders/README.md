# Borders detection
Detects the borders of a given image and colors them in a striking way.

### Compiling

Clone this repository and build the tool using [CMake](http://www.cmake.org/download/).

```sh
$ git clone https://github.com/danielcardeenas/CVision.git
$ cd CVision/Borders/
$ cmake .
$ make
```
### Run
```sh
$ ./Borders <img_to_use.jpg>
```
### Explanation
1. Used Sobel<sub>x</sub> and Sobel<sub>y</sub> kernels for gradients:  [`Convolution()`](https://github.com/danielcardeenas/CVision/blob/master/libs/Filters.cpp#L127)
2. The gradients where combined using euclidian distance [`EuclidianJoin()`](https://github.com/danielcardeenas/CVision/blob/master/libs/Filters.cpp#L293) (altough calculating absulotues is available too [`AbsJoin()`](https://github.com/danielcardeenas/CVision/blob/master/libs/Filters.cpp#L326))
3. To binarize, the threshold applied uses standard deviation as the cut between **0** and **255** [`GetStandardDeviaton()`](https://github.com/danielcardeenas/CVision/blob/master/libs/Utils.cpp#L8)(Mean [`GetMean()`](https://github.com/danielcardeenas/CVision/blob/master/libs/Utils.cpp#L53) and Lazy [`LazyThreshold()`](https://github.com/danielcardeenas/CVision/blob/master/libs/Filters.cpp#L358) thresholding also available). Here it outputs ``binarized.jpg```
4. Special funtion to replace borders colors to output ```final.jpg``` [`SpecialReplacePixels()`](https://github.com/danielcardeenas/CVision/blob/master/libs/Utils.cpp#L121)

### Info
The image used for the **input**: ```img/gears.png```

**Outputs**: ```final.jpg``` and ```binarized.jpg```
