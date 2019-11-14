#!/usr/bin/env python3

last = ''
lat = 0.0
lon = 0.0
alt = 0.0

log = open('aarluk.log', 'r')
out = open('Aarluk.log', 'w')

for line in log:
    if line.startswith('['):
        continue
    out.write(line)
    # key = line.split('=')[0].strip()
    # value = line.split('=')[1].strip()

    # if key == 'anirniq.acquisition.altitude':
    #     alt = float(value)
    # if key == 'anirniq.acquisition.gps.lon':
    #     lon = float(value)
    # if key == 'anirniq.acquisition.gps.lat':
    #     lat = float(value)

    # if lat != 0 and lon != 0 and alt != 0:
    #     out.write('{},{},{} '.format(lon, lat, 0.0))

log.close()
out.close()

