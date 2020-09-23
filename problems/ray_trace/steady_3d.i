h_level = 4
[Mesh]
  uniform_refine = ${h_level}
  [generate]
    # 5mm x 5mm x 6mm
    type = GeneratedMeshGenerator
    dim = 3
    nx = 5
    ny = 5
    nz = 6
    xmax = 0.005
    ymax = 0.005
    zmax = 0.006

    # You can capture a smaller portion of the snow by doing the following
    #nz = 5
    #xmin = 0.002
    #xmax = 0.004
    #ymin = 0.002
    #ymax = 0.004
    #zmin = 0.002
    #zmax = 0.004

  []
[]

[Adaptivity]
  initial_marker = range
  max_h_level = ${h_level}
  initial_steps = ${h_level}
  recompute_markers_during_cycles = true
  [Markers/range]
    type = ValueRangeMarker
    lower_bound = 0.3
    upper_bound = 0.7
    buffer_size = 0.1
    variable = phi
    third_state = DO_NOTHING
  []
[]


[Functions/image]
  type = ImageFunction
  file_base = /Users/slauae/OneDrive/PIKA/msu/0930/0930_rr_rec_tra_bin__Tra
  file_suffix = png
  threshold = 180
  lower_value = 0
  upper_value = 1
  dimensions = '0.005 0.005 0.006'
[]

[Variables/T]
  initial_condition = 263.15
[]

[AuxVariables/phi]
[]

[ICs/phi_ic]
    type = FunctionIC
    function = image
    variable = phi
[]

[Kernels]
  [T_diffusion]
    type = ADHeatConduction
    variable = T
  []
  #[T_source]
  #[]
[]

[BCs]
  [top]
    type = ADNeumannBC
    variable = T
    boundary = top
    value = -100
  []
  [bottom]
    type = ADDirichletBC
    variable = T
    boundary = bottom
    value = 263.15
  []
[]

[Materials]
  [k]
    type = ADParsedMaterial
    args = phi
    f_name = 'thermal_conductivity'
    function = 'phi*2.30+(1-phi)*0.02359'
  []
[]

[Executioner]
  type = Steady
  automatic_scaling = true
  solve_type = NEWTON
  line_search = NONE
  petsc_options_iname = '-pc_type'
  petsc_options_value = 'hypre'
[]

[Outputs]
  exodus = true
[]
