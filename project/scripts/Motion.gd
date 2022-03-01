extends Node


export(NodePath) onready var accelerometer = get_node(accelerometer)
export(NodePath) onready var gyroscope = get_node(gyroscope)


func _process(_delta):
	var a = Sensors.get_accelerometer(0)
	accelerometer.text \
		= str(a.x) + "\n" \
		+ str(a.y) + "\n" \
		+ str(a.z)
	
	var g = Sensors.get_gyroscope(0)
	gyroscope.text \
		= str(g.x) + "\n" \
		+ str(g.y) + "\n" \
		+ str(g.z)
