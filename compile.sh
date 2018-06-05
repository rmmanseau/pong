g++ -c main.cpp helpers.cpp paddle.cpp ball.cpp -I/usr/local/lib
g++ main.o helpers.o paddle.o ball.o -o pong -L/usr/local/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
