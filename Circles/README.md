# Circle detection
Detects the circles of a given image using [Hough transform](http://en.wikipedia.org/wiki/Hough_transform).

### Compiling

Clone this repository and build the project using [CMake](http://www.cmake.org/download/).

```sh
$ git clone https://github.com/danielcardeenas/CVision.git
$ cd CVision/Circles/
$ cmake .
$ make
```
### Run
```sh
$ ./circles <img_to_use.jpg> <[int]threshold (optional)>
```
#####Outputs

```sh
> Centers:
> (260, 144)
> (317, 420)
...
> Time elapsed: 3038 Miliseconds

```


**Centers:** Circle's center coordinates

### Explanation

---------------------------------------

1.  Inside `main.cpp` calls [`DetectCircles()`](https://github.com/danielcardeenas/CVision/blob/master/libs/Utils.cpp#L640). Since each image has his own best values, these are the *tweakable* parameters
  + Threshold (from terminal)
  + Minimum radius accepted
  + Maximum radius accepted
  + Steps to take for each radius iteration

######NOTE:
The function can work without giving any parameters at all, the program can choose their values by [itself](https://github.com/danielcardeenas/CVision/blob/master/libs/Utils.cpp#L672).

2.  Then for each radius value [`HoughCircleTransform()`](https://github.com/danielcardeenas/CVision/blob/master/libs/Utils.cpp#L691) takes charge of filling the accumulator with votes (posible centers of circles) using `x₀ = x - R * cos(θ)` and `y₀ = y - R * sin(θ)`.
3.  In the same iteration [`GetCircles()`](https://github.com/danielcardeenas/CVision/blob/master/libs/Utils.cpp#L735) decides wether or not the votes in the accumulator are centers of circles.
4.  [`DrawCircles()`](https://github.com/danielcardeenas/CVision/blob/master/libs/Utils.cpp#L789), here just draws the circles giving a pair typedef of `center coordinate` and `radius`.

### Samples

#####Threshold: 135

**Input**: ```img/fig.png```
**Outputs**: ```figCircles135.jpg```

<img src="https://raw.githubusercontent.com/danielcardeenas/CVision/master/Circles/img/fig.png" width="320" height="240" />
<img src="https://raw.githubusercontent.com/danielcardeenas/CVision/master/Circles/figCircles135.jpg" width="320" height="240" />

#####Threshold: 90

**Input**: ```img/billar2.jpg```
**Outputs**: ```billar90.jpg```

<img src="https://raw.githubusercontent.com/danielcardeenas/CVision/master/Circles/img/billar2.jpg" width="320" height="240" />
<img src="https://github.com/danielcardeenas/CVision/blob/master/Circles/billar90.jpg" width="320" height="240" />

#####Threshold: Auto

**Input**: ```img/pool6.jpg```
**Outputs**: ```poolAuto.jpg```

<img src="https://raw.githubusercontent.com/danielcardeenas/CVision/master/Circles/img/pool6.jpg" width="320" height="240" />
<img src="https://raw.githubusercontent.com/danielcardeenas/CVision/master/Circles/poolAuto.jpg" width="320" height="240" />

#####Threshold: Auto vs 56

**Input**: ```img/mike.jpg```
**Outputs**: ```mikeAuto.jpg```

<img src="https://raw.githubusercontent.com/danielcardeenas/CVision/master/Circles/img/mike.jpg" width="320" height="240" />
<img src="https://raw.githubusercontent.com/danielcardeenas/CVision/master/Circles/mikeAuto.jpg" width="320" height="240" />
