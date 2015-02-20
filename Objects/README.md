# Objects detection
Detects the objects of a given image

### Compiling

Clone this repository and build the project using [CMake](http://www.cmake.org/download/).

```sh
$ git clone https://github.com/danielcardeenas/CVision.git
$ cd CVision/Objects/
$ cmake .
$ make
```
### Run
```sh
$ ./objects <img_to_use.jpg>
```
### Explanation
+ Calls [`DetectShapes()`](https://github.com/danielcardeenas/CVision/blob/master/libs/Utils.cpp#L271) starts setting a general binarization process of the input image doing the following:

1.  Sobel<sub>x</sub> and Sobel<sub>y</sub> kernels for gradients:  [`Convolution()`](https://github.com/danielcardeenas/CVision/blob/master/libs/Filters.cpp#L214)
2.  The gradients where combined using euclidian distance [`EuclidianJoin()`](https://github.com/danielcardeenas/CVision/blob/master/libs/Filters.cpp#L380) (altough calculating absulotues is available too [`AbsJoin()`](https://github.com/danielcardeenas/CVision/blob/master/libs/Filters.cpp#L413))
3.  To binarize, the threshold applied [`LazyThreshold()`](https://github.com/danielcardeenas/CVision/blob/master/libs/Filters.cpp#L445) uses a constant (128) as the cut between **0** and **255** since the images tested have no noise.
(Standard deviation [`GetStandardDeviaton()`](https://github.com/danielcardeenas/CVision/blob/master/libs/Utils.cpp#L14) 
Mean [`GetMean()`](https://github.com/danielcardeenas/CVision/blob/master/libs/Utils.cpp#L59) and 
Lazy [`LazyThreshold()`](https://github.com/danielcardeenas/CVision/blob/master/libs/Filters.cpp#L445) thresholding also available).

+ This functiongs gets the objects and it's properties [`GetShapes()`](https://github.com/danielcardeenas/CVision/blob/master/libs/Utils.cpp#L316)
+ This one draws the bounding box of the shapes and their names in the image 
[`DrawShapes()`](https://github.com/danielcardeenas/CVision/blob/master/libs/Utils.cpp#L398)

### Samples
**Input**: ```img/circles.jpg```
**Outputs**: ```final.jpg```

<img src="https://github.com/danielcardeenas/CVision/blob/master/Objects/img/circles.jpg?raw=true" width="320" height="240" />
<img src="https://github.com/danielcardeenas/CVision/blob/master/Objects/final.jpg?raw=true" width="320" height="240" />

**Input**: ```img/circles.jpg```
**Outputs**: ```final.jpg```

<img src="https://github.com/danielcardeenas/CVision/blob/master/Objects/img/onepiece.png?raw=true" width="320" height="240" />
<img src="https://github.com/danielcardeenas/CVision/blob/master/Objects/onepiece.jpg?raw=true" width="320" height="240" />
