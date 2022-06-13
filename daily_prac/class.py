class Circle:
	def __init__(self, rad, pi= 3.14) :
		print("hello")
		self.radius = rad
		self.pi = pi
	
	def area(self) : 
		area = self.radius**2 * self.pi
		return area
class Cylinder(Circle):
	def __init__(self, height, radius):
		self.height = height
		#super().__init__(radius)
	def volume(self):
		volume = self.radius**2 * self.pi * self.height
		return volume

c = Cylinder(2, 3)
print(c.volume())
print(c.radius)


