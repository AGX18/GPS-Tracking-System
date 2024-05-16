import folium


def toDegrees(value):
    degree = int(value / 100);
    minutes = value - degree * 100;
    return degree + minutes / 60;


# Open the output file in read mode
with (open('output.csv', 'r') as file):
    # Read the entire content of the file
    data = file.read().strip()
    # Split the content by newlines to get individual GPS coordinates
    long_lat = data.split('\n')
    gps_data = []
    # Iterate over every two lines to extract latitude and longitude and convert them to float
    for i in range(0, len(long_lat), 2):
        lat = toDegrees(float(long_lat[i].strip()))
        lon = toDegrees(float(long_lat[i + 1].strip()))

        gps_data.append((lat, lon))

# Create a map centered at the first GPS coordinate
mymap = folium.Map(location=gps_data[0], zoom_start=20)

folium.Marker(location=gps_data[0]).add_to(mymap)
folium.Marker(location=gps_data[-1], icon=folium.Icon(color='green')).add_to(mymap)  # End marker with red color
# Draw a polyline connecting the GPS coordinates
folium.PolyLine(locations=gps_data, color='#0096FF').add_to(mymap)  # '#0000ff' represents bright blue color

# Save the map to an HTML file
mymap.save("trajectory_map.html")

