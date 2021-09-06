
//This functions needs currect epoch time,time when then epoch time got synced,time when the loops ends.
//
unsigned long  getTime(unsigned long epoch,unsigned long firstMillis,unsigned long lastMillis ) 
{
  unsigned long currenttime;
  if (firstMillis < lastMillis) 
  {
    currenttime = epoch - (firstMillis / 1000) + (lastMillis / 1000);
  }
 if (firstMillis > lastMillis) //This is used to handle rollrover after 49 days(unsigned long can have value only upto 49 days)
 {
    epoch = currenttime;
    currenttime = epoch - (firstMillis / 1000) + (lastMillis / 1000);
  }
  return currenttime;
}
