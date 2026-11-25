mc() {
    g++ $1.cpp -o $1 -Wall -Wextra -Wshadow -O3 -std=c++23
}

nc(){
    g++ $1.cpp -o $1 -Wall -Wextra -Wshadow -DLOCAL 
	-D_GLIBCXX_DEBUG -g -fsanitize=address,undefined -std=c++23
}
