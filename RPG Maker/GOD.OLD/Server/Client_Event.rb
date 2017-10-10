class Event
 
  attr_accessor     :global_event_id
  attr_accessor     :base_id
  attr_accessor     :new_id
  attr_accessor     :map_id
  attr_accessor     :map_x
  attr_accessor     :map_y
  attr_accessor     :map_dir
  attr_accessor     :can_movement
  attr_accessor     :local_switch
  attr_accessor     :stopped
  
  def initialize(global_event_id, base_id, new_id, map_id, map_x, map_y, map_dir, can_movement)
    @global_event_id = global_event_id
    @base_id = base_id
    @new_id = new_id
    @map_id = map_id
    @map_x = map_x
    @map_y = map_y
    @map_dir = map_dir
    @can_movement = can_movement
    @local_switch = ''
    @stopped = true
  end
  
  def update
    if @can_movement == true
      if rand(1) == 1
        @map_x += (rand(2) - 1)
      else
        @map_y += (rand(2) - 1)
      end
    end
    sendmap("<event>#{@global_event_id};#{@base_id};#{@new_id};#{@map_id};#{@map_x};#{@map_y};#{@map_dir};#{@localswitch};#{@stopped}</event>\n")
  end
  
  def sendmap(msg)
    for client in $clients.values
      if client.map_id == @map_id
        client.send(msg)
      end
    end
  end
  
end