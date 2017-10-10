$max_level = 99
$max_arguments = 900
$max_exp = 999999
file = File.open('rpg_levels.txt','w')
file.write("globalvar rpg_levels_needexp\n")
file.write("globalvar rpg_levels_maxhp\n")
file.write("globalvar rpg_levels_maxmp\n")
file.write("globalvar rpg_levels_maxhearts\n")
file.write("globalvar rpg_levels_atk_plus\n")
file.write("globalvar rpg_levels_def_plus\n")
file.write("globalvar rpg_levels_str_plus\n")
file.write("globalvar rpg_levels_con_plus\n")
file.write("globalvar rpg_levels_int_plus\n")
file.write("globalvar rpg_levels_lck_plus\n")
file.write("globalvar rpg_levels__plus\n")
$exp_per_level = $max_exp / $max_level
$args_per_level = $max_arguments / $max_level
@level_needexp = 0
@level_args = $args_per_level
for i in 1..$max_level
  @level_args += $args_per_level
  file.write("global.rpg_levels_needexp[#{i}] = #{@level_needexp}\n")
  file.write("global.rpg_levels_maxhp[#{i}] = #{@level_args}\n")
  file.write("global.rpg_levels_maxmp[#{i}] = #{@level_args}\n")
  file.write("global.rpg_levels_maxhearts[#{i}] = #{@level_args}\n")
  file.write("global.rpg_levels_atk_plus[#{i}] = #{@level_args}\n")
  file.write("global.rpg_levels_def_plus[#{i}] = #{@level_args}\n")
  file.write("global.rpg_levels_str_plus[#{i}] = #{@level_args}\n")
  file.write("global.rpg_levels_con_plus[#{i}] = #{@level_args}\n")
  file.write("global.rpg_levels_int_plus[#{i}] = #{@level_args}\n")
  file.write("global.rpg_levels_lck_plus[#{i}] = #{@level_args}\n")
  @level_needexp += $exp_per_level
end