# Qt TCP IP Big Picture Data Sender
Author: GÖRKEM TOK <br>
Preview video link: https://youtu.be/ej1BmXuZRQw <br>
Email: ceng.gorkem.tok@gmail.com <br>
Linkedin: https://www.linkedin.com/in/gorkem-tok33/ <br>
Language: C++ <br>
<h3> SUMMARY </h3>
In this demo project I am using tcp/ip communication protocol for sending pictures who has large data like 30 mb without data lose or corrupted data. I coded application with c++ and I designed windows with Qt Creator also I used Qt libraries.
<h3> SERVER LOGIC </h3>
<img src = "https://user-images.githubusercontent.com/79594881/120906862-96447f00-c665-11eb-8b8e-2a1c5cb76013.png" width = "270px" height = "400px"> </img>
The server is turning selected picture data to byte array with using buffer. With data stream I am writing buffer data size into byte array before appending  buffer data after that I am appending buffer data into byte array. Finally, writing byte array into socket.
<h3> CLIENT LOGIC </h3>
<img src = "https://user-images.githubusercontent.com/79594881/120906863-9a709c80-c665-11eb-9b3a-496f691626e2.png" width = "270px" height = "400px"> </img>
client waits byte data from server. If detects any byte in socket input, detecting sended data size with using data stream. After that client waits socket byte avaible data until equals to data size. Finally, It reads data up to the size of the data from the socket.
