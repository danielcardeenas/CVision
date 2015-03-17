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
> Time elapsed: 5038 Miliseconds

```


**Centers:** Circle's center coordinates

### Explanation

---------------------------------------

1.  Inside `main.cpp` calls [`DetectCircles()`](https://github.com/danielcardeenas/CVision/blob/master/libs/Utils.cpp#L643). Since each image has his own best values, these are the *tweakable* parameters
  + Threshold (from terminal)
  + Minimum radius accepted
  + Maximum radius accepted
  + Steps to take for each radius iteration

######NOTE:
The function can work without giving any parameters at all, the program can choose their values by [itself](https://github.com/danielcardeenas/CVision/blob/master/libs/Utils.cpp#L672).

2.  Then for each radius value [`HoughCircleTransform()`](https://github.com/danielcardeenas/CVision/blob/master/libs/Utils.cpp#L789) takes charge of filling the accumulator with votes (posible centers of circles) using `x₀ = x - R * cos(θ)` and `y₀ = y - R * sin(θ)`.
3.  In the same iteration [`GetCircles()`](https://github.com/danielcardeenas/CVision/blob/master/libs/Utils.cpp#L830) decides wether or not the votes in the accumulator are centers of circles.
4.  [`~Draw()`](https://github.com/danielcardeenas/CVision/blob/master/libs/Utils.cpp#L730), here just draws the circles giving its center coordinate and radius. (Sorry for the sleepy code here, this should be inside a method).

### Samples
#####Threshold: 100 votes

**Input**: ```img/chessboard1.png```
**Outputs**: ```chess_100.jpg```

<img src="https://raw.githubusercontent.com/danielcardeenas/CVision/master/Lines/img/chessboard1.png" width="320" height="240" />
<img src="https://raw.githubusercontent.com/danielcardeenas/CVision/master/Lines/chess_100.jpg" width="320" height="240" />

#####Threshold: 200 votes

**Input**: ```img/chessboard1.png```
**Outputs**: ```chess_200.jpg```

<img src="https://raw.githubusercontent.com/danielcardeenas/CVision/master/Lines/img/chessboard1.png" width="320" height="240" />
<img src="https://raw.githubusercontent.com/danielcardeenas/CVision/master/Lines/chess_200.jpg" width="320" height="240" />
