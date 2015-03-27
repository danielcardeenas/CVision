# Ellipse detection
Detects the circles of a given image using [This method](http://hci.iwr.uni-heidelberg.de/publications/dip/2002/ICPR2002/DATA/07_3_20.PDF).

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
> Centers:
> Possible ellipse detected: (201, 110) ->203
> Possible ellipse detected: (193, 110) ->214
> Possible ellipse detected: (192, 110) ->216
...
> Time elapsed: 7476 Miliseconds

```


**Centers:** Ellipse's center coordinates->votes

### Explanation

---------------------------------------

1.  Inside `main.cpp` calls [`DetectEllipses()`](https://github.com/danielcardeenas/CVision/blob/master/libs/Utils.cpp#L846). 
2.  Accumulates by minor axis [`DetectEllipses()`](https://github.com/danielcardeenas/CVision/blob/master/libs/Utils.cpp#L959). 

### Samples


######NOTE:
The algorithm runs VERY slow (so the images used in the examples are small) but the accumulator ended up being just one-dimensioned.
Anyways, the method seems to lack on precision so I will implement the normal Hough Transform on this to get better results.
Some modifications to the method have been done in oder to make it work faster.

#####Threshold: auto

**Input**: ```img/ellipse.png```
**Outputs**: ```ellipsemin.png```

<img src="https://raw.githubusercontent.com/danielcardeenas/CVision/master/Ellipses/img/ellipse.png" width="320" height="240" />
<img src="https://raw.githubusercontent.com/danielcardeenas/CVision/master/Ellipses/ellipsemin.png" width="320" height="240" />

#####Threshold: auto

**Input**: ```img/fig2.jpg```
**Outputs**: ```ellipsefig2.jpg```

<img src="https://raw.githubusercontent.com/danielcardeenas/CVision/master/Ellipses/img/fig2.jpg" width="320" height="240" />
<img src="https://raw.githubusercontent.com/danielcardeenas/CVision/master/Ellipses/ellipsefig2.jpg" width="320" height="240" />
