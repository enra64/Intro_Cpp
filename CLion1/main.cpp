#include <iostream>
#include <unitypes.h>

using namespace std;

void wait_a_second(){
    clock_t endwait;
    endwait = clock() + CLOCKS_PER_SEC;
    while(clock() < endwait);
}

void print(const string output){
    cout << output;
}

void println(const string output) {
    cout << output << endl;
}

void wait(){
    for(uint16_t i = 0; i < 3600; i++){
        print("only ");
        cout << (3600 - i);
        println(" seconds left.");
        wait_a_second();
    }
}

int ask(const string question, const initializer_list<string> answers) {
    println(question);
    uint8_t qnr = 0;
    for (string s : answers){
        cout << '\0' + qnr++;
        println(": " + s);
    }
    int answer;
    cin >> answer;
    return answer;
}

int main() {
    int what_to_do = ask("its 9am, you just woke up. what do you want to do?",
        {"do some sports", "go back to sleep"});

    if(what_to_do == 1)
        println("you turn around to get some more sleep, but your conscience compels you to get moving.");

    println("you decide to go for a run, and fall when you trip over a cable. one of your arms hurts.");
    int doctor = ask("the next day, your arm is still hurting. what do you do?",
                         {"go and see a doctor", "just wait it out, it probably is nothing after all."});

    if(doctor == 1)
        println("it is now 2 days later. you cannot move your arm along all degrees of freedom without pain. you go to see the doctor.");

    println("you enter the waiting room after registering yourself at the front desk.");

    int  waiting_room_action = ask("what do you do while you wait?",
        {"play a game on your phone",
         "get some sleep",
         "listen to music",
         "sit still and wait"});

    switch(waiting_room_action){
        case 0:
            println("the mobile game you downloaded before leaving home wants to contact home to activate the licencse.\n"
                    "the waiting room is better shielded than the enterprise, so you have no internet connection. the game refuses to start.");
            break;
        case 1:
            println("you try to sleep, but the kid across the room is bored out of his mind, and keeps you and everyone else awake without mercy.");
            break;
        case 2:
            println("you try to start spotify, but the battery is low. after 10 minutes, the phone shuts down.");
            break;
        default:
            break;
    }

    println("\nit is time to play the waiting game.");

    wait();

    return 0;
}