DIR_PATH_SRC     = src
DIR_PATH_SRC_IMP = $(DIR_PATH_SRC)/$(DIR_NAME_IMP)
DIR_PATH_SRC_IF  = $(DIR_PATH_SRC)/$(DIR_NAME_IF)

$(eval $(call define_object_targets,IMP,\
	$(DIR_PATH_SRC_IMP),\
	,\
	$(DIR_PATH_SRC_IF)\
))
