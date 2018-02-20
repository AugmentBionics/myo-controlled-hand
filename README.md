# myo-controlled-hand

## Raw data 
Run demo.py to see a sample plot of the data.

### Description
There are 3 folders with approximately 60 seconds of Myo sensor activity recorded. Folders named loc_x record power grips, that is just flexing the forearm muscle, in two slightly different locations on the same muscle. The double grips folder recorded a set of quick succession grips which could be detected and used to lock the hand in a fixed position

### Format
t:xx,s:xx,:mxx \n

  * t - time in ms
  * s - sampled analog value from arduino ADC, range 0:1023
  * m - output value from arduino map function map(s, 0, 1023, 0, 179)
