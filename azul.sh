#!/bin/bash

# Prompt for the number of players
while true; do
    read -p "Please input the number of players (2-4): " num_players
    if [[ "$num_players" =~ ^[2-4]$ ]]; then
        break
    else
        echo "Invalid input. Please enter a number between 2 and 4."
    fi
done

# Determine the number of discs based on the number of players
case $num_players in
    2) num_discs=5 ;;
    3) num_discs=7 ;;
    4) num_discs=9 ;;
esac

# Prompt for each player's type (human or AI)
ai_array=()
all_ai=true
for ((i=1; i<=num_players; i++)); do
    while true; do
        read -p "Is player $i a human or AI? (h/a): " player_type
        if [[ "$player_type" == "h" ]]; then
            ai_array+=(0)
            all_ai=false
            break
        elif [[ "$player_type" == "a" ]]; then
            ai_array+=(1)
            break
        else
            echo "Invalid input. Please enter 'h' for human or 'a' for AI."
        fi
    done
done

# Prompt for the number of rounds only if all players are AI, otherwise set to 1
if $all_ai; then
    while true; do
        read -p "Please input the number of rounds: " num_rounds
        if [[ "$num_rounds" =~ ^[0-9]+$ && "$num_rounds" -gt 0 ]]; then
            break
        else
            echo "Invalid input. Please enter a positive integer."
        fi
    done

    # Prompt to see AI gameplay details
    while true; do
        read -p "Do you want to see AI gameplay details? (y/n): " show_ai_details
        if [[ "$show_ai_details" == "y" ]]; then
            result_only=0
            break
        elif [[ "$show_ai_details" == "n" ]]; then
            result_only=1
            break
        else
            echo "Invalid input. Please enter 'y' for yes or 'n' for no."
        fi
    done
else
    num_rounds=1
    result_only=0
fi

# Modify azul.c with macOS-compatible sed
sed -i "" "9s/.*/#define n_player $num_players/" azul.c
sed -i "" "10s/.*/#define n_disc $num_discs/" azul.c

ai_array_str="$(IFS=,; echo "${ai_array[*]}")"
sed -i "" "55s/.*/int ai[$num_players]= {${ai_array_str}};/" azul.c
sed -i "" "54s/.*/int result_only=$result_only;/" azul.c
sed -i "" "85s/.*/int pl, play = $num_rounds;/" azul.c
sed -i "" "86s/.*/int ai_only=$result_only;/" azul.c

echo "azul.c has been successfully updated."