extends GridContainer


export(NodePath) var cursor
var previous_position = Vector2(-1, -1)


func _ready():
	cursor = get_node(cursor)


func _process(_delta):
	if len(Touchpads.get_touches(0)) > 0:
		var average = Touchpads.get_average(0)
		var rect = get_viewport_rect()
		var position = Vector2(rect.size.x * average.x, rect.size.y * average.y)
		
		if $Absolute.pressed:
			cursor.position = position
		else:
			if previous_position.x == -1:
				previous_position = position
			else:
				var diff = position - previous_position
				diff.x *= $XSensitivity.value
				diff.y *= $YSensitivity.value
				
				$Movement.text = str(diff)
				cursor.position += diff
				
				if cursor.position.x < 0: cursor.position.x = 0
				elif cursor.position.x > rect.size.x: cursor.position.x = rect.size.x
				
				if cursor.position.y < 0: cursor.position.y = 0
				elif cursor.position.y > rect.size.y: cursor.position.y = rect.size.y
				
				previous_position = position
	else:
		previous_position = Vector2(-1, -1)
