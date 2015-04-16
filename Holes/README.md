# Ellipse detection
Detects the circles of a given image using [This method](http://hci.iwr.uni-heidelberg.de/publications/dip/2002/ICPR2002/DATA/07_3_20.PDF).
Some modifications to the method have been done in oder to make it work faster.

### Compiling

Clone this repository and build the project using [CMake](http://www.cmake.org/download/).

```sh
$ git clone https://github.com/danielcardeenas/CVision.git
$ cd CVision/Ellipses/
$ cmake .
$ make
```
### Run
```sh
$ ./ellipse <img_to_use.jpg> <[int]threshold (optional)>
```
#####Outputs

```sh
> Hole0 Dimensions: 3x43
> Hole1 Dimensions: 39x193
> Hole2 Dimensions: 2x54
> Hole3 Dimensions: 3x13
> Hole4 Dimensions: 3x22
...
> Time elapsed: 5 Miliseconds

```


**Dimensions:** Holes bounding-box area

### Explanation

---------------------------------------

1.  Inside `main.cpp` calls [`DetectHoles()`](https://github.com/danielcardeenas/CVision/blob/master/libs/NewUtils.cpp#L8). 
2.  DFS only selected whites by histogram (This improves speed a lot by ignoring everything else) [`DFSHist()~~`](https://github.com/danielcardeenas/CVision/blob/master/libs/NewUtils.cpp#L46). 

### Samples


######NOTE:
The algorithm detects holes even when the inside of them its white / black.


**Input**: ```img/bullet2.jpg```
**Outputs**: ```outbullet2.jpg```

<img src="https://raw.githubusercontent.com/danielcardeenas/CVision/master/Holes/img/bullet2.jpg" width="320" height="240" />
<img src="https://raw.githubusercontent.com/danielcardeenas/CVision/master/Holes/outbullet2.jpg" width="320" height="240" />

**Input**: ```img/bullet.jpg```
**Outputs**: ```outbullet.jpg```

<img src="https://raw.githubusercontent.com/danielcardeenas/CVision/master/Holes/img/bullet.jpg" width="320" height="240" />
<img src="https://raw.githubusercontent.com/danielcardeenas/CVision/master/Holes/outbullet.jpg" width="320" height="240" />

**Input**: ```img/wall3.png```
**Outputs**: ```outwall3.jpg```

<img src="https://raw.githubusercontent.com/danielcardeenas/CVision/master/Holes/img/wall3.png" width="320" height="240" />
<img src="https://raw.githubusercontent.com/danielcardeenas/CVision/master/Holes/outwall3.jpg" width="320" height="240" />