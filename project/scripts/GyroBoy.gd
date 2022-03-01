extends KinematicBody


const HALF_PI = PI / 2
var gyro_sensitivity = Vector2(.05, 0.05)

var previous_angle = 0.0
var set_prev = true

export(NodePath) onready var x_sensitivity = get_node(x_sensitivity)
export(NodePath) onready var y_sensitivity = get_node(y_sensitivity)
export(NodePath) onready var dampen_values = get_node(dampen_values)


func _ready():
	$Camera.make_current()


func _process(_delta):
	gyro_sensitivity.x = x_sensitivity.value
	gyro_sensitivity.y = y_sensitivity.value
	
	# Vertical View Reset
	var reset_x = Input.is_action_pressed("reset_x")
	if reset_x:
		$Camera.rotation.x = 0
	
	# Gyro
	if !Input.is_action_pressed("ignore_gyro"):
		var gyro = Sensors.get_gyroscope(0)
		
		if dampen_values.pressed:
			gyro.x = stepify(gyro.x, .01)
			gyro.y = stepify(gyro.y, .01)
		
		rotate_y(gyro.y * gyro_sensitivity.y)
		
		if !reset_x:
			$Camera.rotate_x(gyro.x * gyro_sensitivity.x)
			
			if abs($Camera.rotation.x) > HALF_PI:
				$Camera.rotation.x = HALF_PI * sign($Camera.rotation.x)
	
	# Flick Stick
	var stick = Vector2(
		Input.get_action_strength("latlook_x+")
		- Input.get_action_strength("latlook_x-"),
		Input.get_action_strength("latlook_y+")
		- Input.get_action_strength("latlook_y-"))
	
	if stick.length() > .7:
		var current_angle = stick.angle()
		if set_prev:
			rotate_y(-(HALF_PI + current_angle))
			
			previous_angle = current_angle
			set_prev = false
		
		var diff = -wrapf(current_angle - previous_angle, -PI, PI)
		rotate_y(diff)
		
		previous_angle = current_angle
	else:
		set_prev = true
