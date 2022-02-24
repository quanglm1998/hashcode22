main: main.cpp
	g++ -O2 -std=c++17 -DLOCAL -o main main.cpp

quang: quang.cpp
	g++ -O2 -std=c++17 -DLOCAL -o main quang.cpp

all:
	g++ -DLOCAL -std=c++17 -o scorer -O2 scorer.cpp

run:
	./main <a_an_example.in.txt >a_an_example.out.txt
	./main <b_better_start_small.in.txt >b_better_start_small.out.txt
	./main <c_collaboration.in.txt >c_collaboration.out.txt
	./main <d_dense_schedule.in.txt >d_dense_schedule.out.txt
	./main <e_exceptional_skills.in.txt >e_exceptional_skills.out.txt
	./main <f_find_great_mentors.in.txt >f_find_great_mentors.out.txt

eval:
	./scorer a_an_example.in.txt a_an_example.out.txt
	./scorer b_better_start_small.in.txt b_better_start_small.out.txt
	./scorer c_collaboration.in.txt c_collaboration.out.txt
	./scorer d_dense_schedule.in.txt d_dense_schedule.out.txt
	./scorer e_exceptional_skills.in.txt e_exceptional_skills.out.txt
	./scorer f_find_great_mentors.in.txt f_find_great_mentors.out.txt