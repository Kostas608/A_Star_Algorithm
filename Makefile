default:
	gcc Main.c -o main.exe

clean:
	-rm -f main.exe

run:
	./main.exe
