[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 5
  ny = 5
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
  [./phi]
  [../]
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
  [./phi_func]
    type = ParsedFunction
    value = t*x*y
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
    type = UserForcingFunction
    variable = u
    function = forcing_func
  [../]
[]

[AuxKernels]
  [./phi_kernel]
    type = FunctionAux
    variable = phi
    function = phi_func
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
  [../]
  [./ndofs]
    type = NumDOFs
  [../]
  [./hmax]
    type = AverageElementSize
    variable = u
  [../]
[]

[Executioner]
  type = Steady
[]

[Outputs]
  output_initial = true
  console = true
  exodus = true
[]

[ICs]
  [./u_ic]
    function = u_func
    variable = u
    type = FunctionIC
  [../]
  [./phi_ic]
    function = phi_func
    variable = phi
    type = FunctionIC
  [../]
[]
