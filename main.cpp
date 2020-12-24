#include "qstd.h"
using namespace qstd;
#include <QList>

    if (nb >= 0 and control[start] != control[end]){
        
    }
    else if (nb == -2 and control[start] == control[end]){

    }

static int gene[65];
static int win_count_player_1 = 1;
static int win_count_player_2 = 1;
static int draw_count = 1;
static int generation = 1;
static int nb_of_generation = 1000;


int * get_action_player2(int control[], int number[])
{
    static int action[4];
    int i;
    int num = 0;
    for (i = 0; i < 5; i++){
        if (control[i] == 2 and num < number[i]){
            num = number[i];
            action[0] = i;
        }
        if (control[i] != 2){
            action[1] = i;
        }
    }
    action[2] = -1;
    if (number[action[0]] >= number[action[1]]){
        action[2] = number[action[0]];
        action[3] = control[action[0]];
    }
    else{
        num = 0;
        for (i = 0; i < 5; i++){
            if (control[i] == 2 and i != action[0] and num < number[i]){
                num = number[i];
                action[1] = i;
                action[2] = -2;
            }
        }
    }

    return action;
}

int * get_action_player1(int control[], int number[], int start = -1, int end = -1)
{
    static int action[4];
    static int ran[4];
    int i;
    int num = 0;
    if (start == -1){
        for (i = 0; i < 5; i++){
            if (control[i] == 1 and number[i] != 0){
                num++;
                ran[i] = i;
            }
        }
        action[0] = ran[qrand()%num];
        do{
            action[1] = qrand()%5;
        }while(action[0] == action[1]);
    }else{
        action[0] = start;
        action[1] = end;
    }
    action[2] = -1;
    if (number[action[0]] >= number[action[1]]){
        action[2] = number[action[0]];
        action[3] = control[action[0]];
    }
    else{
        num = 0;
        for (i = 0; i < 5; i++){
            if (control[i] == 1 and i != action[0] and num < number[i]){
                num = number[i];
                action[1] = i;
                action[2] = -2;
            }
        }
    }

    return action;
}

void attack(int start, int end, int nb, int new_control, int *control, int *base_nb){
    if (nb >= 0 and control[start] != control[end]){
        if (base_nb[end] < nb){
            base_nb[end] = nb - base_nb[end];
        }
        else{
            base_nb[end] = nb - base_nb[end];
        }

        base_nb[start] -= nb;
        control[end] = new_control;
        cout<<"Player "<<control[start]<<" : Base "<<(end)+1<<" is attacked by base "<<start+1<<" with "<<(nb)<<" soldiers \n\n";
    }
    else if (nb == -2 and control[start] == control[end]){
        base_nb[start] += base_nb[end];
        cout<<"Player "<<control[start]<<" : Base "<<(start)+1<<" receive "<<base_nb[end]<<" soldier from base "<<(end)+1<<"\n\n";
        base_nb[end] = 0;
    }
}

int total_soldier(int *control, int *nb, int player){
    int i;
    int num = 0;
    for (i = 0; i < 5; i++){
        if (control[i] == player){
            num += nb[i];
        }
    }
    return num;
}

void genome(int *gen){
    int i;
    int num = 0;
    int index = 0;
    for (i = 0; i < 10; i++){
        if (gen[5 + i * 6] < num){
            num = gen[5 + i * 6];
            index = i;
        }
    }
    gen[1 + index * 6] = -1;
    gen[2 + index * 6] = -1;
    gen[3 + index * 6] = -1;
    gen[4 + index * 6] = -1;
}

int main()
{
    GENE:
    int base_nb[5] = {50, 0, 0, 0, 50};
    int base_control[5] = {1, 0, 0, 0, 2};
    int turn = 0;
    int *p;
    int *w;
    int i;
    cout<<"\n******************************************************************\n";
    cout<<"************************* Generation: "<<generation<<" **************************\n";
    cout<<"******************************************************************\n\n";
    while (true){
        cout<<"---------------------------- Turn n "<<turn<<" ----------------------------\n\n";
        p = get_action_player2(base_control, base_nb);
        attack(*p, *(p+1), *(p+2), *(p+3), &base_control[0], &base_nb[0]);
        if (generation == 1 or gene[1 + turn * 6] == -1){
            w = get_action_player1(base_control, base_nb);
            attack(*w, *(w+1), *(w+2), *(w+3), &base_control[0], &base_nb[0]);

            gene[0 + turn * 6] = turn;
            gene[1 + turn * 6] = *w;
            gene[2 + turn * 6] = *(w+1);
            gene[5 + turn * 6] = total_soldier(&base_control[0], &base_nb[0], 1);
        }
        else{
            w = get_action_player1(base_control, base_nb, gene[1 + turn * 6], gene[2 + turn * 6]);
            attack(gene[1 + turn * 6], gene[2 + turn * 6], *(w+2), *(w+3), &base_control[0], &base_nb[0]);
        }

        for (i = 0; i < 5; i++){
            if (base_control[i] != 0){
                base_nb[i]++;
            }
            cout<<"Base "<<i+1<<" as "<<base_nb[i]<<" soldiers controled by player "<<base_control[i]<<"\n";

        }
        if (base_control[2] != 0){
            base_nb[2]++;
        }
        cout<<"\n";

        if (total_soldier(&base_control[0], &base_nb[0], 1) == 0 or total_soldier(&base_control[0], &base_nb[0], 2) == 0){
            cout<<"Player "<<base_control[0]<<" win the game in "<<turn<<" turn. GG \n";
            if (base_control[0] == 1){
                win_count_player_1++;
            }
            else{
                win_count_player_2++;
            }
            break;
        }

        if (turn == 10){
           if (total_soldier(&base_control[0], &base_nb[0], 1) > total_soldier(&base_control[0], &base_nb[0], 2)){
               cout<<"Timeout player 1 win with "<<total_soldier(&base_control[0], &base_nb[0], 1)<<" soldiers. GG\n";
               win_count_player_1++;
           }
           else if (total_soldier(&base_control[0], &base_nb[0], 1) < total_soldier(&base_control[0], &base_nb[0], 2)){
               cout<<"Timeout player 2 win with "<<total_soldier(&base_control[0], &base_nb[0], 2)<<" soldiers. GG\n";
               win_count_player_2++;
           }
           else{
               cout<<"Timeout draw. GG\n";
               draw_count++;
           }
           break;
        }
        turn++;
    }
    generation++;
    genome(&gene[0]);
    if (generation < nb_of_generation+1){
        goto GENE;
    }
    cout<<"\nPlayer 1 won "<<win_count_player_1 - 1<<" times.\n";
    cout<<"Player 2 won "<<win_count_player_2 - 1<<" times.\n";
    cout<<"Draw "<<draw_count - 1<<" times.\n\n";

}
