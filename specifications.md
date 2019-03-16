# Specifications

## Possible actions by the client:

- PLACE_OFFERING_MARKER {god, offering, player}
- CONNECT {name}


## Servers check by Action

PLACE_OFFERING_MARKER:
	- offering not greater than money
	- player not already on same god
	- no player with same offering on same god
	

