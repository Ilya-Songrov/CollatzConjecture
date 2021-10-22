## How to build (Ubuntu 20.04)
```
sudo apt-get install libgmp-dev -y
git clone <this_repo>
cd <this_repo>
git checkout master
git pull
mkdir build
cd build
g++ ../main1.cpp -lgmpxx -lgmp
g++ ../main2.cpp -lgmpxx -lgmp
```

