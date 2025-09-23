extends RigidBody2D

@export var speed = 500
@export var jump_power = 800
@export var starting_health = 3

signal score_changed(amount: int, player: Node2D)
signal health_changed(health: int, max_health: int, player: Node2D)
signal damaged(amount: int, player: Node2D)
signal healed(amount: int, player: Node2D)
signal death(player: Node2D)
signal won_level(player: Node2D)
signal iframes_start(player: Node2D)
signal iframes_stop(player: Node2D)

var coins: int
var score: int
var health: int
var max_health: int
var invincible: bool
var enabled: bool

var ray: RayCast2D

# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	ray = $RayCast2D
	$Camera2D.make_current()
	
	score = 0
	health = starting_health
	max_health = starting_health
	invincible = false
	enabled = true
	
	score_changed.emit(score, self)
	health_changed.emit(health, max_health, self)

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta: float) -> void:
	pass

func _physics_process(delta):
	var input = Vector2.ZERO
	
	if enabled:
		if Input.is_action_pressed("move_right"):
			input.x += 1
		if Input.is_action_pressed("move_left"):
			input.x -= 1

		input = input.normalized()
		linear_velocity.x = input.x * speed
		angular_velocity = 0
		rotation = 0
		
		if Input.is_action_just_pressed("jump") and ray.is_colliding():
			apply_impulse(Vector2.UP * jump_power)
	else:
		linear_velocity = Vector2.ZERO

func get_score():
	return score
	
func add_score(amount: int):
	score += amount
	score_changed.emit(score, self)

func damage(amount: int, ignore_invincible=false):	
	if !invincible || ignore_invincible:
		if health - amount <= 0:
			health = 0
			die()
		else:
			iframes()
			health -= amount
			
		damaged.emit(amount, self)
		health_changed.emit(health, max_health, self)
	
func heal(amount: int):
	health = min(max_health, health + amount)
	healed.emit(amount, self)
	health_changed.emit(health, max_health, self)

func iframes():
	invincible = true
	$IFramesTimer.start()
	iframes_start.emit(self)

func stop_iframes():
	invincible = false
	iframes_stop.emit(self)
	
func _on_i_frames_timer_timeout() -> void:
	stop_iframes()
	
func win_level():
	won_level.emit(self)
	queue_free()

func die():
	enabled = false
	death.emit(self)
