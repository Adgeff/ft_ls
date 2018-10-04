# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/24 17:11:19 by geargenc          #+#    #+#              #
#    Updated: 2018/10/04 09:32:06 by geargenc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SILENT			:

NAME			=	ft_ls

CC				= 	gcc

CFLAGS			=	-Wall -Wextra -Werror -I includes

FILES			=	ft_addarg.c\
					ft_badargs.c\
					ft_blk.c\
					ft_blocks.c\
					ft_buff.c\
					ft_chr.c\
					ft_cmp_f.c\
					ft_color.c\
					ft_config_blocksize.c\
					ft_config_colors1.c\
					ft_config_colors2.c\
					ft_config.c\
					ft_datatab.c\
					ft_dir.c\
					ft_dirtitle_f.c\
					ft_exeperm.c\
					ft_explore_f.c\
					ft_explore_tools.c\
					ft_fifo.c\
					ft_fileargs.c\
					ft_freecolortab.c\
					ft_freelist.c\
					ft_ftypetab.c\
					ft_getsuffix_f.c\
					ft_gettime_f.c\
					ft_gid.c\
					ft_gidprint_f.c\
					ft_gidsize_f.c\
					ft_inode.c\
					ft_link.c\
					ft_lnk.c\
					ft_majmin.c\
					ft_mode.c\
					ft_name.c\
					ft_nlink.c\
					ft_optset1.c\
					ft_optset2.c\
					ft_optset3.c\
					ft_optset4.c\
					ft_optset5.c\
					ft_optset6.c\
					ft_permtabs.c\
					ft_print_col_tools1.c\
					ft_print_col_tools2.c\
					ft_print_f.c\
					ft_print_size.c\
					ft_print.c\
					ft_readarg_f.c\
					ft_readargv.c\
					ft_readperm.c\
					ft_reg.c\
					ft_select_f.c\
					ft_size.c\
					ft_sizeprint_f.c\
					ft_sizesize_f.c\
					ft_sock.c\
					ft_sort_f.c\
					ft_sort_tools.c\
					ft_suffix.c\
					ft_time.c\
					ft_timeprint_f.c\
					ft_timetools.c\
					ft_totalprint.c\
					ft_uid.c\
					ft_uidprint_f.c\
					ft_uidsize_f.c\
					ft_wht.c\
					ft_writeperm.c\
					main.c\
					str_tools1.c\
					str_tools2.c

SRC_DIR			=	src/

SRC				=	$(addprefix $(SRC_DIR), $(FILES))

OBJ_DIR			=	obj/

OBJ				=	$(addprefix $(OBJ_DIR), $(FILES:.c=.o))

DEP_DIR			=	dep/

DEP				=	$(addprefix $(DEP_DIR), $(FILES:.c=.d))

all				:	$(NAME)

$(DEP_DIR)%.d	:	$(SRC_DIR)%.c
	@mkdir -p $(DEP_DIR)
	@$(CC) $(CFLAGS) -MM $< -MT $(OBJ_DIR)$*.o -MF $@
	@printf "\r\E[K\033[1;33mCreated : $@\033[0m"

-include $(DEP)

$(OBJ_DIR)%.o	:	$(SRC_DIR)%.c Makefile
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "\r\E[K\033[1;33mCreated : $@\033[0m"

$(NAME)			:	$(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $@
	@printf "\r\E[K\033[1;32mCreated : $@\033[0m\n"

clean			:
	@rm -rf obj
	@printf "\033[1;31mRemoved : $(OBJ_DIR)\033[0m\n"
	@rm -rf dep
	@printf "\033[1;31mRemoved : $(DEP_DIR)\033[0m\n"

fclean			:	clean
	@rm -f $(NAME)
	@printf "\033[1;31mRemoved : $(NAME)\033[0m\n"

re				:
	@$(MAKE) $(MFLAGS) fclean
	@$(MAKE) $(MFLAGS) all

.PHONY			:	all clean fclean re
