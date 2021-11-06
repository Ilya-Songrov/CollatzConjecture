### Collatz conjecture
It is also known as the 3n + 1 problem, the 3n + 1 conjecture, the Ulam conjecture.

![Screen Shot](md/maxresdefault.jpg)

## How to build (Ubuntu 20.04)
```
sudo apt-get install libgmp-dev -y

git clone <this_repo>
cd <this_repo>
git checkout master
git pull
mkdir build
cd build
g++ ../main1.cpp -lgmpxx -lgmp -o collatzConjecture1
g++ ../main2.cpp -lgmpxx -lgmp -o collatzConjecture2
```

## See video 
https://www.youtube.com/watch?v=094y1Z2wpJg&ab_channel=Veritasium (image from here)

