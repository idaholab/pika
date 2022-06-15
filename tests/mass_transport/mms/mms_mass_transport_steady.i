[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 10
  ny = 10
  elem_type = QUAD4
[]

[Adaptivity]
  marker = refine
  steps = 3
  [./Markers]
    [./refine]
      type = UniformMarker
      mark = refine
    [../]
  [../]
[]

[Variables]
  [./u]
    order = FIRST
    family = LAGRANGE
  [../]
[]

[AuxVariables]
  [./abs_error]
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
    type = Diffusion
    variable = u
    block = 0
  [../]
  [./mms]
    type = BodyForce
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

[PikaMaterials]
  phase = -1
  temperature = 273.15
[]

[Postprocessors]
  [./L2_error]
    type = ElementL2Error
    variable = u
    function = u_func
    execute_on = 'initial timestep_end'
  [../]
  [./ndofs]
    type = NumDOFs
    execute_on = 'initial timestep_end'
  [../]
  [./hmax]
    type = AverageElementSize
    execute_on = 'initial timestep_end'
  [../]
[]

[Executioner]
  type = Steady
  nl_rel_tol = 1e-12
[]

[Outputs]
  console = true
  csv = true
  exodus = true
[]

[ICs]
  [./u_ic]
    function = u_func
    variable = u
    type = FunctionIC
  [../]
[]
