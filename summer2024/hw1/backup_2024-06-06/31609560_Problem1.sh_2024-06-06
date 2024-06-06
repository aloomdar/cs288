#!/bin/bash 

function computerChoice()
{
num=$(((RANDOM % 3) + 1))

case $num in
    1) compChoice="rock";;
    2) compChoice="paper";;
    3) compChoice="scissors";;
    *) echo "Error somehow";;
esac

echo $compChoice
}

function game()
{

if [ "$1" == "rock" ] && [ "$2" = "rock" ]; then
	echo "You chose $1" 
	echo "Computer chose $2"
    echo "Tie! Try again"
    echo "What is your choice?"
    read choice
	newComp=$(computerChoice)
    game ${choice} ${newComp}
elif [ "$1" == "rock" ] && [ "$2" == "paper" ]; then
	echo "You chose $1" 
	echo "Computer chose $2"
    echo "You lose! NOT NOICE!" 
elif [ "$1" == "rock" ] && [ "$2" == "scissors" ]; then
	echo "You chose $1"
	echo "Computer chose $2"
    echo "You win! NOICE!"
elif [ "$1" == "paper" ] && [ "$2" == "paper" ]; then
	echo "You chose $1"
	echo "Computer chose $2"
    echo "Tie! Try again" 
    echo "What is your choice?"
    read choice
	newComp=$(computerChoice)
    game ${choice} ${newComp}
elif [ "$1" == "paper" ] && [ "$2" == "rock" ]; then
	echo "You chose $1"
	echo "Computer chose $2"
    echo "You win! NOICE!"
elif [ "$1" == "paper" ] && [ "$2" == "scissors" ]; then
	echo "You chose $1"
	echo "Computer chose $2"
    echo "You lost. NOT NOICE!"
elif [ "$1" == "scissors" ] && [ "$2" == "scissors" ]; then
	echo "You chose $1" 
	echo "Computer chose $2"
    echo "Tie! Try again" 
    echo "What is your choice?"
    read choice
	newComp=$(computerChoice)
    game ${choice} ${newComp}
elif [ "$1" == "scissors" ] && [ "$2" == "paper" ]; then
	echo "You chose $1"
	echo "Computer chose $2"
    echo "You win! NOICE!"
elif [ "$1" == "scissors" ] && [ "$2" == "rock" ]; then
    echo "You chose $1"
	echo "Computer chose $2"
	echo "You lost. NOT NOICE!"
fi  
}


echo "Hello! Let's play rock paper scissors"
echo "The rules are simple:"
echo "Enter 'rock' to choose rock"
echo "Enter 'paper' to choose paper"
echo "Enter 'scissors' to choose scissors"
echo "You are player 1. What is your choice? "

read choice
p2choice=$(computerChoice)

game ${choice} ${p2choice}

