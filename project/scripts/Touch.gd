extends Node


export(NodePath) onready var average = get_node(average)
export(NodePath) onready var touches = get_node(touches)


func _process(_delta):
	var a = Touchpads.get_average(0)
	average.text = str(a.x, ", ", a.y, ", ", a.z)
	
	var text = ""
	for t in Touchpads.get_touches(0):
		text += str(t.x) + ", " + str(t.y) + ", " + str(t.z) + "\n"
	
	touches.text = text
