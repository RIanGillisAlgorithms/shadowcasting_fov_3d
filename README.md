# shadowcasting_fov_3d
A simple 3d shadow-casting fov algorithm

## Positives
* No multiplication/ divison

## Negatives
* The tileCubes that lie on the view frustum edges are calculated 3 times (i.e. where slope is equal to (1,1), (1,-1), (-1,1), (-1,-1)), once each for x, y & z
* An int queue is used to  