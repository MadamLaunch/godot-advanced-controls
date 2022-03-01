extends Node


export(NodePath) onready var compiled = get_node(compiled)
export(NodePath) onready var linked = get_node(linked)
export(NodePath) onready var controller = get_node(controller)


func _ready():
	var sdl = Sensors.get_sdl_versions()
	compiled.text = sdl[0]
	linked.text = sdl[1]
	controller.text = Touchpads.get_name(0)
