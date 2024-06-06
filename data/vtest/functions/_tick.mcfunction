scoreboard players add .tick timer 1
execute if score .exec bool matches 1 as @e[type=marker,tag=start] at @s run function vtest:_insert_path
