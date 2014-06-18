[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 10
  ny = 10
  elem_type = QUAD4
[]

[Variables]
  [./u]
    order = FIRST
    family = LAGRANGE
  [../]
[]

[Functions]
  [./u_func]
    type = ParsedFunction
    vars = a
    vals = 4
    value = sin(a*pi*x)
  [../]
  [./forcing_func]
    type = ParsedFunction
    vars = a
    vals = 4
    value = a*a*pi*pi*sin(a*pi*x)
  [../]
[]

[Kernels]
  [./u_diff]
    # D_name = diffusion_coefficient
    type = Diffusion
    variable = u
    block = 0
  [../]
  [./f]
    type = UserForcingFunction
    variable = u
    function = forcing_func
  [../]
[]

[BCs]
  [./all]
    type = FunctionDirichletBC
    variable = u
    boundary = 'bottom left right top'
    function = u_func
  [../]
[]

[Postprocessors]
  [./L2_error]
    type = ElementL2Error
    variable = u
    function = u_func
  [../]
  [./h_max]
    type = AverageElementSize
    variable = u
  [../]
  [./ndofs]
    type = NumDOFs
  [../]
[]

[Executioner]
  type = Steady
  petsc_options_iname = '-pc_type -pc_hypre_type'
  petsc_options_value = 'hypre boomeramg'
[]

[Adaptivity]
  marker = refine
  steps = 6
  [./Markers]
    [./refine]
      type = UniformMarker
      mark = refine
    [../]
  [../]
[]

[Outputs]
  exodus = true
  csv = true
[]

[ICs]
  [./u_ic]
    function = u_func
    variable = u
    type = FunctionIC
  [../]
[]
