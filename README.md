#


Install required libs:
```
sudo apt-get install  cmake gcc g++  build-essential libgl1-mesa-dev libxtst-dev build-essential libqt4-dev qt4-qmake

```

Clone repository
```
 git clone https://github.com/Herdu/sieci2-klient.git .
 ```

Build
```
cd client
qmake -qt=qt4
make
```

Run
```
./client
```
