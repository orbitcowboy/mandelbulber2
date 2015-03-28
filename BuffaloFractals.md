# Introduction #

By adding absolute operators to a combination of the iterated x,y,z values of the "Mandelbulb Classis Power 2" some interesting 3D fractals can be generated.

# Original Mandelbulb classis power 2 code #
```
	double x2 = z.x * z.x;
	double y2 = z.y * z.y;
	double z2 = z.z * z.z;
	double temp = 1.0 - z2 / (x2 + y2);
	double newx = (x2 - y2) * temp;
	double newy = 2.0 * z.x * z.y * temp;
	double newz = -2.0 * z.z * sqrt(x2 + y2);
	z.x = newx;
	z.y = newy;
	z.z = newz;
```

# The variations of the Buffalo #

## Buffalo 1 ##
| abs(x) |
|:-------|
| y |
| z |

## Buffalo 2 ##
| x |
|:--|
| abs(y) |
| z |

## Buffalo 3 ##
| x |
|:--|
| y |
| abs(z) |

## Buffalo 4 ##
| abs(x) |
|:-------|
| abs(y) |
| z |

## Buffalo 5 ##
| abs(x) |
|:-------|
| y |
| abs(z) |

## Buffalo 6 ##
| x |
|:--|
| abs(y) |
| abs(z) |

## Buffalo 7 ##
| abs(x) |
|:-------|
| abs(y) |
| abs(z) |