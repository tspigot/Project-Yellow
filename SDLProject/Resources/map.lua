map = {}
tiles = {}

height = -1
width = -1

TILE_EMPTY = 0
TILE_BLOCKING = 1

tiles["."] = {tile_type = TILE_EMPTY, filename = "tile-empty.png"}
tiles["x"] = {tile_type = TILE_BLOCKING, filename = "tile-blocking.png"}

map_string = [[
. . . . . . . . . .
. . . . . . . . . .
. . . . x . . . . .
. . . x . . . . . .
. . . . . . . . . .
. . . . . . . . . .
. . . . . . . . . .
. . . . . . . . . .
. . . . . . . . . .
. . . . . . . . . .
]]

function parse_map_string(str)
	local i = 0
	for line in string.gmatch(str, '[^\n]+') do
		local j = 0
		map[i] = {}
		for char in string.gmatch(line, "[^%s]") do 
			map[i][j] = char
			j = j + 1
		end
		width = j
		i = i + 1
	end
	height = i
end

function get_height()
	return height
end

function get_width()
	return width
end

function get_tile(x,y)
	return map[y][x]
end

function get_type_string()
	local i = ""
	for k, v in pair(tiles) do
		i = i + k
	end
	return i
end

function get_tile_type(char)
	return tiles[char].tile_type
end

function get_tile_filename(char)
	return tiles[char].filename
end

function parse()
	parse_map_string(map_string)
end